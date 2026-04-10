system.userActivationScripts.archeclipseSync = {
  text = ''
    # Current Date: ${builtins.currentTime} 
    # ^ This line forces Nix to see the script as "new" every time you rebuild
    
    TARGET_USER="your_actual_username"
    HOME_DIR="/home/$TARGET_USER"

    echo "Running ArchEclipse Sync for $TARGET_USER..."

    # Create .config if it doesn't exist
    mkdir -p "$HOME_DIR/.config"

    # Clone directly into a temporary location if the main folder is missing
    if [ ! -d "$HOME_DIR/ArchEclipse" ]; then
      ${pkgs.git}/bin/git clone --depth 1 https://github.com/AymanLyesri/ArchEclipse.git "$HOME_DIR/ArchEclipse"
    fi

    # Sync the files
    if [ -d "$HOME_DIR/ArchEclipse/.config" ]; then
      cp -ra "$HOME_DIR/ArchEclipse/.config/." "$HOME_DIR/.config/"
      chown -R $TARGET_USER:users "$HOME_DIR/.config"
      chown -R $TARGET_USER:users "$HOME_DIR/ArchEclipse"
      echo "Sync completed successfully."
    fi
  '';
};
