system.userActivationScripts.archeclipseSync = {
  text = ''
    USER_HOME="/home/yourusername" # Change this to your actual username
    CONF_DIR="$USER_HOME/.config"
    
    # Create config dir if missing
    mkdir -p "$CONF_DIR"

    # Only clone if we haven't already
    if [ ! -d "$USER_HOME/ArchEclipse" ]; then
      ${pkgs.git}/bin/git clone --depth 1 https://github.com/AymanLyesri/ArchEclipse.git "$USER_HOME/ArchEclipse"
      
      # Copying the .config folder content
      # We use 'cp -rs' to symlink if possible, or 'cp -a' for simple copy
      cp -a "$USER_HOME/ArchEclipse/.config/." "$CONF_DIR/"
      
      # Fix permissions so your user owns the files
      chown -R yourusername:users "$USER_HOME/ArchEclipse"
      chown -R yourusername:users "$CONF_DIR"
    fi
  '';
};
