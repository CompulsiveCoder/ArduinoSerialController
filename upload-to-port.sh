echo "Uploading to port $1"

pio run --target upload --environment uno --upload-port $1
