REQUIREMENTS

This installation is for Fedora 36/CentOS/RHEL Distributions: 

```
sudo dnf install glib-devel NetworkManager-libnm-devel
```

If the above installtion fails, use the following format to track what dependency to install

```
sudo dnf whatcontains "*/<header file name>"
```

```
glib.h
NetworkManager.h
```
