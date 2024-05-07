#!/bin/sh
echo ""
echo "Sprite Bug Test ROM Build Script"
echo "---------------------------------"

sdcc="${HOME}/Code/sdcc-4.2.0/bin/sdcc"
devkitSMS="${HOME}/Code/devkitSMS"
SMSlib="${devkitSMS}/SMSlib"
ihx2sms="${devkitSMS}/ihx2sms/Linux/ihx2sms"


build_test_rom ()
{
    echo "Building Test ROM..."

    mkdir -p build
    echo "Compiling..."
    ${sdcc} -c -mz80 --peep-file ${devkitSMS}/SMSlib/src/peep-rules.txt -I ${SMSlib}/src -o "build/main.rel" "main.c" || exit 1

    echo ""
    echo "Linking..."
    ${sdcc} -o build/test_rom.ihx -mz80 --no-std-crt0 --data-loc 0xC000 ${devkitSMS}/crt0/crt0_sms.rel build/*.rel ${SMSlib}/SMSlib.lib || exit 1

    echo ""
    echo "Generating ROM..."
    ${ihx2sms} build/test_rom.ihx test_rom.sms || exit 1

    echo ""
    echo "Done"
}

# Clean up any old build artefacts
rm -rf build

build_test_rom
