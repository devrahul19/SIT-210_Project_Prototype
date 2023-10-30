import RPi.GPIO as GPIO
from mfrc522 import SimpleMFRC522

# Initialize the RFID reader
reader = SimpleMFRC522()

# Initialize the buzzer
buzzer_pin = 17  # Adjust this to the actual GPIO pin number
GPIO.setmode(GPIO.BCM)
GPIO.setup(buzzer_pin, GPIO.OUT)

# Authorized RFID card ID(s)
authorized_card_id = "YOUR_AUTHORIZED_CARD_ID"

try:
    while True:
        print("Place your RFID card near the reader...")
        card_id, _ = reader.read()

        if str(card_id) == authorized_card_id:
            print("Access granted. Welcome!")
        else:
            print("Unauthorized card detected. Intrusion detected!")
            # Activates the buzzer and alerts the users within the Premises
            GPIO.output(buzzer_pin, GPIO.HIGH)
            input("Press Enter to stop the alarm.")  # Wait for user acknowledgment
            GPIO.output(buzzer_pin, GPIO.LOW)

except KeyboardInterrupt:
    pass

finally:
    GPIO.cleanup()
    reader.cleanup()
