home-manager.users.yourusername = { pkgs, ... }: {   # ← make sure "yourusername" is your real username
  home.stateVersion = "25.11";   # ← ADD THIS LINE (use 25.11 or 24.11 depending on your nixpkgs)

  # ArchEclipse dotfiles
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
};