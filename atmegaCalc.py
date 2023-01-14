from tkinter import *
from tkinter import ttk
import serial

com_1 = serial.Serial(port='COM3', baudrate=9600, timeout=1,
                      parity=serial.PARITY_EVEN, rtscts=1,
                      stopbits=1)

def calculate():
    msg = bytes(value_one.get() + ';' + sign.get() + value_two.get() + '&', 'UTF-8')
    com_1.write(msg)

ops = ['+', '-', '*', '/']

root = Tk()
root.title("ISIS Calculator")
root.geometry("300x100+600+200")
Button(root, text="Посчитать", command=calculate).grid(row=2,column=3)
value_one = Entry(root, width=5)
value_one.grid(row=2,column=0)
sign = ttk.Combobox(root, values=ops, state="readonly", width=5)
sign.grid(row=2,column=1)
value_two = Entry(root, width=5)
value_two.grid(row=2,column=2)

root.mainloop()
