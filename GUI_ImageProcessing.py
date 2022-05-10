# -*- coding: utf-8 -*-

from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog
import json
import os
import fileinput
import shutil
import argparse
from subprocess import Popen, PIPE, STDOUT

config_dict = {}
entered_path = ""
#----------------------------------------------------------------------------------------------------------------------#



class App(tk.Tk):
    def __init__(self):
        super().__init__()

        # configure the root window
        self.title('My Awesome App')
        self.geometry('300x50')

        # label
        self.label = ttk.Label(self, text='Hello, Tkinter!')
        self.label.pack()

        # button
        self.button = ttk.Button(self, text='Click Me')
        self.button['command'] = self.button_clicked
        self.button.pack()

    def button_clicked(self):
        showinfo(title='Information',
                 message='Hello, Tkinter!')


if __name__ == "__main__":
    app = App()
    app.mainloop()

#class Main_Menu(ttk.Frame):
 #   """ Main Menu for App/GUI """

  #  def _

#Main loop
   # window.mainloop()

#if __name__ == '__main__':
 #   main()