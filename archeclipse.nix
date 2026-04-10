{ pkgs, ... }: 
let
  # This downloads the repo as a static folder in the Nix Store
  archeclipse-src = fetchTarball {
    url = "https://github.com/AymanLyesri/ArchEclipse/archive/master.tar.gz";
  };
in
{
  system.userActivationScripts.archeclipseSync = {
    text = ''
      # 1. Set your username correctly here
      TARGET_USER="your_actual_username"
      HOME_DIR="/home/$TARGET_USER"

      echo "Syncing ArchEclipse files from the Nix Store..."

      # 2. Ensure the .config directory exists
      mkdir -p "$HOME_DIR/.config"

      # 3. Copy the files from the Nix Store to your home folder
      # Using 'cp' instead of 'ln' to avoid "Read-only file system" errors in scripts
      cp -ra "${archeclipse-src}/.config/." "$HOME_DIR/.config/"

      # 4. Fix permissions so YOU own the files, not root
      chown -R $TARGET_USER:users "$HOME_DIR/.config"
      
      echo "ArchEclipse sync complete!"
    '';
  };
}
