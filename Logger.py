import logging

# Logger configuration
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s - %(message)s",
    handlers=[
        logging.StreamHandler(),  # Logs to console
        logging.FileHandler("stadium.log")  # Logs to file
    ]
)

def log(message):
    logging.info(message)
