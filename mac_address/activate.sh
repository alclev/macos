#!/bin/bash

# Check if the script is being run as root
if [[ $EUID -ne 0 ]]; then
    echo "This script must be run as root. Please try again with sudo."
    exit 1
fi

# Get the interface name for which you want to change the MAC address
interface="en0" # Replace "en0" with your desired interface name

# Generate a random MAC address
new_mac=$(openssl rand -hex 6 | sed 's/\(..\)/\1:/g; s/.$//')

# Disable the interface
ifconfig "$interface" down

# Change the MAC address
ifconfig "$interface" ether "$new_mac"

# Enable the interface
ifconfig "$interface" up

# Verify the new MAC address
ifconfig "$interface" | grep ether

echo "MAC address successfully changed to $new_mac on $interface."

