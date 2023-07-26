import libspdr

def main():
    instance = libspdr.Client("localhost", 8080)
    assert instance.connect() == 0
    assert instance.disconnect() == 0

if __name__ == "__main__":
    main()