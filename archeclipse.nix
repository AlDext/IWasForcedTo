{
  description = "My NixOS configuration with Home Manager and ArchEclipse";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";   # or nixos-25.11 if you prefer stable

    home-manager = {
      url = "github:nix-community/home-manager";
      inputs.nixpkgs.follows = "nixpkgs";
    };

    archeclipse = {
      url = "github:AymanLyesri/ArchEclipse";
      flake = false;   # This is important — it's just files, not a Nix flake
    };
  };

  outputs = { self, nixpkgs, home-manager, archeclipse, ... }: {
    nixosConfigurations.nixos = nixpkgs.lib.nixosSystem {   # ← change "nixos" to your actual hostname if different
      system = "x86_64-linux";   # change to aarch64-linux only if you're on ARM (like Raspberry Pi)

      modules = [
        ./configuration.nix   # your main system config (hardware, packages, etc.)

        # Integrate Home Manager into NixOS (so one rebuild does everything)
        home-manager.nixosModules.home-manager
        {
          home-manager.useGlobalPkgs = true;
          home-manager.useUserPackages = true;

          # Replace "yourusername" with your actual login username
          home-manager.users.yourusername = { config, pkgs, ... }: {
            imports = [ ];   # you can add ./home.nix later if you want to split it

            # === ArchEclipse dotfiles go here ===
            home.file = {
              ".config" = {
                source = "${archeclipse}/.config";
                recursive = true;
              };

              ".zshrc" = {
                source = "${archeclipse}/.zshrc";
              };

              ".icons" = {
                source = "${archeclipse}/.icons";
                recursive = true;
              };
            };

            # Optional: make Hyprland reload after changes
            wayland.windowManager.hyprland.enable = true;   # if not already enabled in configuration.nix
          };
        }
      ];
    };
  };
}