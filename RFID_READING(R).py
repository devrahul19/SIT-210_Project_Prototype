from mfrc522 import SimpleMFRC522

# Initialize the RFID reader
reader = SimpleMFRC522()

try:
    while True:
        print("Place your RFID card near the reader...")
        card_id, _ = reader.read()
        print("Card ID:", card_id)
        # Rest of the code...
