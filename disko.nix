{
  disko.devices = {
    disk = {
      # Treat Partition 8 as a standalone disk for Boot
      nixos-boot = {
        device = "/dev/nvme0n1p8";
        type = "disk";
        content = {
          type = "filesystem";
          format = "vfat";
          mountpoint = "/boot";
          mountOptions = [ "umask=0077" ];
        };
      };
      # Treat Partition 9 as a standalone disk for the Btrfs Root
      nixos-root = {
        device = "/dev/nvme0n1p9";
        type = "disk";
        content = {
          type = "btrfs";
          extraArgs = [ "-f" ]; # Overwrite existing data on p9
          subvolumes = {
            "@" = {
              mountpoint = "/";
              mountOptions = [ "compress=zstd" "noatime" ];
            };
            "@nix" = {
              mountpoint = "/nix";
              mountOptions = [ "compress=zstd" "noatime" ];
            };
            "@home" = {
              mountpoint = "/home";
              mountOptions = [ "compress=zstd" "noatime" ];
            };
          };
        };
      };
    };
  };
}
