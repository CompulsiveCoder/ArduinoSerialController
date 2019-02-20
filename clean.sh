#pio run --target clean

SOURCE_FILE="src/LightPRSensorCalibratedLight/LightPRSensorCalibratedLight.ino"

sed -i "s/#define VERSION .*/#define VERSION \"1-0-0-0\"/" $SOURCE_FILE
