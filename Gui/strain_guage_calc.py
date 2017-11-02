import matplotlib.pyplot as plt
import tkinter as tk
from openpyxl import Workbook
from tkinter.filedialog import askopenfilename, askdirectory
from PIL import ImageTk, Image
import sys, os

def resource_path(relative_path):
    try:
        base_path = getattr(sys, '_MEIPASS', os.path.dirname(os.path.abspath(__file__)))
    except:
        base_path = os.path.abspath(".")

    return os.path.join(base_path, relative_path)

def init_gui():
    root = tk.Tk()
    app = SG_GUI(root)
    root.mainloop()


class SG_GUI(tk.Frame):

    def __init__(self, parent, *args, **kwargs):
        tk.Frame.__init__(self, parent)
        self.parent = parent

        self.resistors = [0] * 10
        self.cypress_parse_filename = '-'
        self.excel_destination = '-'

        parent.minsize(width=750, height=750)
        parent.maxsize(width=750, height=750)
        parent.title("Strain Gauge GUI")

        title_page = tk.Label(parent, text="Flexible Electronics GUI")
        title_page.grid(row=0, column=0)

        calculate_button = tk.Button(self.parent, text="Calculate Proper Gain", command=lambda: [self.update_resistors(), self.calculate_strain()])
        calculate_button.grid(row=1, column=0)

        close_button = tk.Button(self.parent, text="Close", command=parent.quit)
        close_button.grid(row=1, column=1)

        cypress_ble_button = tk.Button(self.parent, text="Upload Cypress BLE Log", command=lambda: self.cypress_ble_pop_up())
        cypress_ble_button.grid(row=1, column=2)

        self.r1_label = tk.Label(self.parent, text="R1 value in ohm")
        self.r1_label.grid(row=2, column=0)
        self.er1 = tk.IntVar(self.parent)
        self.er1.set(self.resistors[0])
        self.er1_entry = tk.Entry(self.parent, textvariable=self.er1, width=10)
        self.er1_entry.grid(row=2, column=1)

        self.r2_label = tk.Label(self.parent, text="R2 value in ohm")
        self.r2_label.grid(row=3, column=0)
        self.er2 = tk.IntVar(self.parent, value=self.resistors[1])
        self.er2_entry = tk.Entry(self.parent, textvariable=self.er2, width=10)
        self.er2_entry.grid(row=3, column=1)

        self.r3_label = tk.Label(self.parent, text="R3 value in ohm")
        self.r3_label.grid(row=4, column=0)
        self.er3 = tk.IntVar(self.parent, value=self.resistors[2])
        self.er3_entry = tk.Entry(self.parent, textvariable=self.er3, width=10)
        self.er3_entry.grid(row=4, column=1)

        self.r4_label = tk.Label(self.parent, text="R4 value in ohm")
        self.r4_label.grid(row=5, column=0)
        self.er4 = tk.IntVar(self.parent, value=self.resistors[3])
        self.er4_entry = tk.Entry(self.parent, textvariable=self.er4, width=10)
        self.er4_entry.grid(row=5, column=1)

        self.r5_label = tk.Label(self.parent, text="R5 value in ohm")
        self.r5_label.grid(row=6, column=0)
        self.er5 = tk.IntVar(self.parent, value=self.resistors[4])
        self.er5_entry = tk.Entry(self.parent, textvariable=self.er5, width=10)
        self.er5_entry.grid(row=6, column=1)

        self.r6_label = tk.Label(self.parent, text="R6 value in ohm")
        self.r6_label.grid(row=7, column=0)
        self.er6 = tk.IntVar(self.parent, value=self.resistors[5])
        self.er6_entry = tk.Entry(self.parent, textvariable=self.er6, width=10)
        self.er6_entry.grid(row=7, column=1)

        self.rx_label = tk.Label(self.parent, text="Rx (ohm)")
        self.rx_label.grid(row=8, column=0)
        self.erx = tk.IntVar(self.parent, value=self.resistors[6])
        self.erx_entry = tk.Entry(self.parent, textvariable=self.erx, width=10)
        self.erx_entry.grid(row=8, column=1)

        self.rx_tol_label = tk.Label(self.parent, text="Rx Tolerance (ohm)")
        self.rx_tol_label.grid(row=8, column=2)
        self.erx_tol = tk.IntVar(self.parent, value=self.resistors[7])
        self.erx_tol_entry = tk.Entry(self.parent, textvariable=self.erx_tol, width=10)
        self.erx_tol_entry.grid(row=8, column=3)

        self.rg1_label = tk.Label(self.parent, text="RG1")
        self.rg1_label.grid(row=9, column=0)
        self.rg1 = tk.IntVar(self.parent, value=self.resistors[8])
        self.rg1_value = tk.Label(self.parent, textvariable=self.rg1)
        self.rg1_value.grid(row=9, column=1)

        self.rg2_label = tk.Label(self.parent, text="RG2")
        self.rg2_label.grid(row=10, column=0)
        self.rg2 = tk.IntVar(self.parent, value=self.resistors[9])
        self.rg2_value = tk.Label(self.parent, textvariable=self.rg2)
        self.rg2_value.grid(row=10, column=1)

        self.bg_raw = Image.open(resource_path("Background_Circuit.png"))
        self.bg_rs_img = self.bg_raw.resize((750, 375), Image.ANTIALIAS)
        self.bg_img = ImageTk.PhotoImage(self.bg_rs_img)
        self.bg_label = tk.Label(self.parent, image=self.bg_img)
        self.bg_label.grid(row=11, column=0, rowspan=2, columnspan=6)


        self.resistor_entries = [self.er1_entry, self.er2_entry, self.er3_entry, self.er4_entry, self.er5_entry,
                                 self.er6_entry, self.erx_entry, self.erx_tol_entry]
        self.resistor_var = [self.er1, self.er2, self.er3, self.er4, self.er5,
                                 self.er6, self.erx, self.erx_tol, self.rg1, self.rg2]

    def update_resistors(self):
        for i in range(0, 8):
            self.resistors[i] = int(self.resistor_entries[i].get())
            self.resistor_var[i].set(self.resistors[i])
        print(self.resistors)

    def calculate_strain(self):
        rg1 = self.resistors[0]*5
        rg2 = self.resistors[0] * 5
        self.resistor_var[8].set(rg1)
        self.resistor_var[9].set(rg2)

    def ask_user_file(self, file_show):
        self.cypress_parse_filename = askopenfilename()
        file_show.delete(0, tk.END)
        file_show.insert(0, self.cypress_parse_filename)

    def ask_user_output_folder(self, folder_show):
        self.excel_destination = askdirectory()
        folder_show.delete(0, tk.END)
        folder_show.insert(0, self.excel_destination)

    def cypress_ble_pop_up(self):
        popup_cypress = tk.Toplevel()
        popup_cypress.grab_set()
        popup_cypress.geometry("1000x100")
        popup_cypress.wm_title("Cypress BLE Data Upload")
        label = tk.Label(popup_cypress, text="Upload Cypress BLE Data Log")
        label.grid(row=0, column=0)

        b3 = tk.Button(popup_cypress, text="Browse for DataLog File:", command=lambda: self.ask_user_file(file_show))
        b3.grid(row=1, column=0)

        cypress_filename_string_var = tk.StringVar(popup_cypress, value = self.cypress_parse_filename)
        file_show = tk.Entry(popup_cypress, textvariable = cypress_filename_string_var, width = 150)
        file_show.grid(row=1, column=1)

        b4 = tk.Button(popup_cypress, text="Select Output Folder:", command=lambda: self.ask_user_output_folder(folder_show))
        b4.grid(row=2, column=0)

        excel_destination_string_var = tk.StringVar(popup_cypress, value = self.excel_destination)
        folder_show = tk.Entry(popup_cypress, textvariable = excel_destination_string_var, width = 150)
        folder_show.grid(row=2, column=1)

        b1 = tk.Button(popup_cypress, text="Select this DataLog File", command=lambda:self.parse_cypress_ble(popup_cypress, cypress_filename_string_var.get(), excel_destination_string_var.get()))
        b1.grid(row=3, column=0)

        b2 = tk.Button(popup_cypress, text="Cancel", command=popup_cypress.destroy)
        b2.grid(row=3, column=1)

        popup_cypress.mainloop()

    def parse_cypress_ble(self, popup_window, source_file_name, destination_file_name):
        popup_window.destroy()
        cypress_datalog_file = str(source_file_name)
        cypress_excel_file = str(destination_file_name)
        cypress_datalog = open(cypress_datalog_file, 'r')
        cypress_datalog_lines = cypress_datalog.readlines()
        cypress_datalog.close()

        TMP116_Data = []  # Temperature Data in Celcius from TMP116
        Time_Stamp = []  # Time Stamp
        seconds = []  # Time Since Data has been Captured
        counter = 0
        notification = "[Health Thermometer Service|Health Thermometer Measurement] Notification received with value"
        for i in range(len(cypress_datalog_lines)):
            str_temp = ''.join(cypress_datalog_lines.__getitem__(i))

            if notification in str_temp:
                str1_parts = str_temp.split(" , ")
                time_str = ''.join(str1_parts.__getitem__(0))
                temp_str = ''.join(str1_parts.__getitem__(2))
                time_str_temp = time_str[1:-1]
                time_str_date, time_str_clock = time_str_temp.split("|")
                temp_hex = ''.join(temp_str.split(" ").__getitem__(3)) + ''.join(temp_str.split(" ").__getitem__(2))
                temp_dec = int(temp_hex, 16)
                temp_celcius = temp_dec * 7812.5 / 1000000
                TMP116_Data.append(temp_celcius)
                Time_Stamp.append(time_str_temp)
                seconds.append(counter)
                counter = counter + 1

        dest_filename = cypress_excel_file + '/' + time_str_date + '.xlsx'
        png_filename = cypress_excel_file + '/' + time_str_date + '.png'
        wb = Workbook()
        ws = wb.active
        ws.title = "Sample #1"
        ws.cell(row=1, column=1, value="Time Stamp")
        ws.cell(row=1, column=2, value="Seconds")
        ws.cell(row=1, column=3, value="TMP116 (C)")
        wb.save(filename=dest_filename)
        for i in range(1, len(seconds)):
            ws.cell(row=i + 1, column=1, value=Time_Stamp[i - 1])
            ws.cell(row=i + 1, column=2, value=seconds[i - 1])
            ws.cell(row=i + 1, column=3, value=TMP116_Data[i - 1])

        wb.save(filename=dest_filename)

        plt.plot(seconds, TMP116_Data)
        plt.ylabel('Temperature (C)')
        plt.xlabel('Time (s)')
        plt.title('TMP116 Temperature')
        plt.savefig(png_filename)
        plt.show()

def main():
    init_gui()

if __name__ == "__main__":
    main()
