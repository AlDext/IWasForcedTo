{ pkgs, ... }: 
let
  # This "pre-fetches" the ArchEclipse code into the Nix Store
  archeclipse-src = pkgs.fetchFromGitHub {
    owner = "AymanLyesri";
    repo = "ArchEclipse";
    rev = "master"; # Or a specific commit hash
    sha256 = "0000000000000000000000000000000000000000000000000000"; 
    # Tip: Run the rebuild, it will fail and tell you the REAL hash. 
    # Copy the "got:" hash and paste it here.
  };
in
{
  # Now we just symlink the files
  system.userActivationScripts.archeclipseSync = {
    text = ''
      TARGET_USER="your_actual_username"
      HOME_DIR="/home/$TARGET_USER"
      
      mkdir -p "$HOME_DIR/.config"
      
      # Link the folders from the Nix Store to your home
      ln -sfn "${archeclipse-src}/.config/hypr" "$HOME_DIR/.config/hypr"
      ln -sfn "${archeclipse-src}/.config/ags" "$HOME_DIR/.config/ags"
      
      chown -h $TARGET_USER:users "$HOME_DIR/.config/hypr"
      chown -h $TARGET_USER:users "$HOME_DIR/.config/ags"
    '';
  };
}
