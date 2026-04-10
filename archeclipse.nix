system.userActivationScripts.archeclipseSync = {
  text = ''
    # Use your actual username here
    TARGET_USER="yourusername" 
    TARGET_HOME="/home/$TARGET_USER"
    
    # Ensure git is available and the network can be reached
    echo "Starting ArchEclipse Sync for $TARGET_USER..."

    if [ ! -d "$TARGET_HOME/ArchEclipse" ]; then
      # Run as the actual user to avoid permission headaches
      sudo -u $TARGET_USER ${pkgs.git}/bin/git clone --depth 1 https://github.com/AymanLyesri/ArchEclipse.git "$TARGET_HOME/ArchEclipse"
    fi

    if [ -d "$TARGET_HOME/ArchEclipse/.config" ]; then
      echo "Copying configs..."
      # Use -n to avoid overwriting files you've already customized
      cp -ra "$TARGET_HOME/ArchEclipse/.config/." "$TARGET_HOME/.config/"
      chown -R $TARGET_USER:users "$TARGET_HOME/.config"
    else
      echo "Error: Source .config not found in cloned repo!"
    fi
  '';
};
