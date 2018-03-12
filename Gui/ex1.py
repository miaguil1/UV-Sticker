import serial_2 as sp1

def main():
    while 1:
        try:
            # sp1.flush_input()
            # print(sp1.text_to_decimal())
            #print(sp1.text_to_decimal())
            # part1 = sp1.read_8()
            # part2 = sp1.read_8()
            # print(part1)
            # print(part2)
            uvi = sp1.read_dec()
            print("UVI: " + str(uvi))

            print(sp1.read_text())
            # chipID = sp1.read_8()
            # print("ChipID: " + str(chipID))

            # temp = sp1.read_dec()
            # print("UVI: " + uvi)

            # print(sp1.text_to_decimal())

        except sp1.SerialTimeoutException:
            print('Data could not be read')


if __name__ == "__main__":
    main()
