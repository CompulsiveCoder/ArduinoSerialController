echo "Uploading to port $1"

pio run -s --target upload --environment uno --upload-port $1
