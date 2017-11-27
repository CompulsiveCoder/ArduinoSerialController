# update
sudo apt-get update &&

# python
sudo apt-get install -y curl python &&

# platform.io
sudo python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"

# Or

#pip install -U platformio