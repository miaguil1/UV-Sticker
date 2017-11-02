import serial_2 as sp1

def main():
    while 1:
        try:
            # sp1.flush_input()
            # print(sp1.text_to_decimal())
            #print(sp1.text_to_decimal())
            # number1 = sp1.read_8()
            # print(number1)
            number2 = sp1.read_dec()
            print(number2)
            # print(sp1.text_to_decimal())

        except sp1.SerialTimeoutException:
            print('Data could not be read')


if __name__ == "__main__":
    main()
