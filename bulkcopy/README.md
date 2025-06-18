# bulkcopy

## About

Prepares for and executes a bulk copy operation (e.g. copying multiple
terabytes of data from one network share to another.) Useful in situations
where reliability is a concern, since one a job has been created, it can
be restarted, retried, etc.

## Notes

* LinuxCIFS is a useful package that enables mounting Windows, macOS, or
  linux shares. To install on Debian and derivatives:

  # Upgrade package list
  sudo apt update && sudo apt upgrade

  # Install cifs utils
  sudo apt install cifs-utils psmisc

  # Test installation
  mount -t cifs   # should succeed without error
  fuser           # should run and display message

