# Encrypter : GUI v1.0.3 : Andrew Woo (c) 2017 - present
# Email: seungminleader@gmail.com
# Website: flamingthanatos.github.io
# Project Page: flamingthanatos.github.io/projects/encrypter/encrypter.htm


# * This software is an extension of Encrypter by Andrew Woo
# * The function of this software is to act as the GUI of
#    Encrypter.
#
# * This software is licensed under the MIT License.

# Copyright (c) 2018 Andrew Woo
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# *** Warning to Potential Users/Buyers ***
# The original copy of this software is available @ flamingthanatos.github.io/projects/encrypter/encrypter.htm,
# free of charge.
# This version of the software may have been modified, and therefore may not be the exact, unmodified
# copy distributed by the original creater.


# Top Level Imports
import tkinter as tk
import tkinter.ttk as ttk

import os
import subprocess
import pyautogui

import ctypes.wintypes


# -- Code by user axil on Stackoverflow -- #
CSIDL_PERSONAL = 5       # My Documents
SHGFP_TYPE_CURRENT = 1   # Get current, not default value

md_path = ctypes.create_unicode_buffer(ctypes.wintypes.MAX_PATH)
ctypes.windll.shell32.SHGetFolderPathW(None, CSIDL_PERSONAL, None, SHGFP_TYPE_CURRENT, md_path)
# https://stackoverflow.com/questions/6227590/finding-the-users-my-documents-path #


class Preview:

    def __init__(self, _root):

        self._root = _root

        self.preview = tk.Text(self._root, width=43, height=5)
        self.preview.grid(row=0, column=0, rowspan=2, columnspan=5)

        self.p_text = ''
        self.p_alg = '-a xor'
        self.p_pass = '-p 7825'
        self.p_input = '-l'
        self.p_ainput = 'default value'
        self.p_output = '-oto=line'
        self.p_o_type = '-oto=line'

        self.out_path = ''

        self.out_text = ''

    def update_alg(self, algorithm='xor'):
        self.p_alg = '-a ' + algorithm.lower()
        self.update()

    def update_pass(self, password='7825'):
        self.p_pass = '-p ' + password.replace(' ', '').strip()
        self.update()

    def input_type(self, input_t='-l'):
        self.p_input = input_t
        self.update()

    def actual_input(self, ainput=''):
        self.p_ainput = ainput.replace('\n', '')
        self.update()

    def update_output(self, otype='line', path=''):

        if otype == 'line':
            self.p_output = '-oto=line'
            self.p_o_type = '-oto=line'
        elif otype == 'file':
            self.p_output = '-oto=file ' + path
            self.p_o_type = '-oto=file'

        self.out_path = path

        self.update()

    def update(self):

        self.preview.config(state=tk.NORMAL)
        self.preview.delete("1.0", tk.END)

        self.p_text = self.p_alg + ' ' + self.p_pass + ' ' + self.p_input + ' ' + self.p_ainput + ' ' + self.p_output

        self.preview.insert(tk.INSERT, 'INPUT PREVIEW:\n' + self.p_text)
        self.preview.config(state=tk.DISABLED)

    def get_output(self, outputted):

        self.preview.config(state=tk.NORMAL)
        self.preview.delete("1.0", tk.END)

        if self.p_output == '-oto=line':
            self.out_text = 'OUTPUT:\n' + outputted.rstrip()
        else:
            if self.out_path != '':
                self.out_text = 'Data output completed! Please check file.\n' + self.out_path
            else:
                self.out_text = 'Data output completed! Please check file.\n' + md_path.value + r'\__def_enc_output.txt'

        self.preview.insert(tk.INSERT, self.out_text)
        self.preview.config(state=tk.DISABLED)

    def ret_(self):
        return self.p_text, self.p_o_type


# Step 1
class Step1:

    def __init__(self, _root, _preview):
        self._root = _root

        # Step 1 vars
        self.strstep1 = tk.StringVar()
        self.strstep1.set('STEP 1: Choose Algorithm')
        self.step1 = tk.Label(self._root, textvariable=self.strstep1, relief=tk.FLAT)
        self.step1.config(font=('Veranda', 11, 'bold italic'))
        self.step1.grid(padx=3, row=3, column=0, columnspan=5, sticky='W')

        self.str_alg_type = tk.StringVar()
        self.str_alg_type.set('-algorithm:')
        self.alg_type = tk.Label(self._root, textvariable=self.str_alg_type, relief=tk.FLAT)
        self.alg_type.config(font=('Veranda', 10))
        self.alg_type.grid(padx=3, row=4, column=0, sticky='W')

        self.comboalg_values = tk.StringVar()
        self.comboalg = ttk.Combobox(self._root, textvariable=self.comboalg_values, state='readonly')
        self.comboalg['values'] = ('XOR', 'RBEA')
        self.comboalg.current(0)
        self.comboalg.grid(row=4, column=1, sticky='W')
        self.comboalg.bind("<<ComboboxSelected>>", lambda e: self.getselectedalg(_preview))

    def getselectedalg(self, _preview):
        _preview.update_alg(algorithm=self.comboalg_values.get())


# Step 2
class Step2:

    def __init__(self, _root, _preview):
        self._root = _root

        # Step 1 vars
        self.strstep2 = tk.StringVar()
        self.strstep2.set('STEP 2: Enter Password')
        self.step2 = tk.Label(self._root, textvariable=self.strstep2, relief=tk.FLAT)
        self.step2.config(font=('Veranda', 11, 'bold italic'))
        self.step2.grid(padx=3, row=5, column=0, columnspan=5, sticky='W')

        self.str_pass = tk.StringVar()
        self.str_pass.set('-password:')
        self.pass_txt = tk.Label(self._root, textvariable=self.str_pass, relief=tk.FLAT)
        self.pass_txt.config(font=('Veranda', 10))
        self.pass_txt.grid(padx=3, row=6, column=0, sticky='W')

        self.pass_entry = tk.Entry(_root, width=35)
        self.pass_entry.grid(row=6, column=1, columnspan=4, sticky='W')
        self.pass_entry.bind("<Key>", self.getpassword)

        self.fullpass = ''

    def getpassword(self, event):
        self.fullpass = self.pass_entry.get()

        _preview.update_pass(self.fullpass)

        if event.keycode != 17:
            pyautogui.press('ctrl')


# Step 3
class Step3:

    def __init__(self, _root, _preview):
        self._root = _root
        self._preview = _preview

        self.strstep3 = tk.StringVar()
        self.strstep3.set('STEP 3: Choose Input Type')
        self.step3 = tk.Label(self._root, textvariable=self.strstep3, relief=tk.FLAT)
        self.step3.config(font=('Veranda', 11, 'bold italic'))
        self.step3.grid(padx=3, row=7, column=0, columnspan=5, sticky='W')

        self.b_file = tk.Button(self._root, text='-file', width=12, relief='groove', bg='#d3d3d3', command=self.file) \
            .grid(padx=5, row=8, column=0, sticky='W')
        self.b_line = tk.Button(self._root, text='-line', width=12, relief='groove', bg='#d3d3d3', command=self.line) \
            .grid(padx=100, row=8, column=0, columnspan=2, sticky='E')

    def line(self):
        self._preview.input_type(input_t='-l')

    def file(self):
        self._preview.input_type(input_t='-f')


# Step 4
class Step4:

    def __init__(self, _root, _preview):
        self._root = _root
        self._preview = _preview

        self.strstep4 = tk.StringVar()
        self.strstep4.set('STEP 4: Enter Input (String or Path)')
        self.step4 = tk.Label(self._root, textvariable=self.strstep4, relief=tk.FLAT)
        self.step4.config(font=('Veranda', 11, 'bold italic'))
        self.step4.grid(padx=3, row=9, column=0, columnspan=5, sticky='W')

        self.userinput = tk.Text(self._root, width=40, height=5)
        self.userinput.grid(row=10, column=0, rowspan=2, columnspan=5)

        self.userinput.bind("<Key>", self.getinput)

        self.fullinput = ''

    def getinput(self, event):
        self.fullinput = self.userinput.get('1.0', tk.END)
        self._preview.actual_input(ainput=self.fullinput)

        if event.keycode != 17:
            pyautogui.press('ctrl')


# Step 5
class Step5:

    def __init__(self, _root, _preview):
        self._root = _root
        self._preview = _preview

        self.strstep5 = tk.StringVar()
        self.strstep5.set('STEP 5: Choose Output Type')
        self.step5 = tk.Label(self._root, textvariable=self.strstep5, relief=tk.FLAT)
        self.step5.config(font=('Veranda', 11, 'bold italic'))
        self.step5.grid(padx=3, row=12, column=0, columnspan=5, sticky='W')

        self.b_line = tk.Button(self._root, text='line', width=47, relief='groove', bg='#d3d3d3', command=self.line) \
            .grid(row=13, column=0, columnspan=5)
        self.b_file = tk.Button(self._root, text='file', width=47, relief='groove', bg='#d3d3d3', command=self.file) \
            .grid(row=15, column=0, columnspan=5)

        self.path_entry = tk.Entry(_root, width=55)
        self.path_entry.grid(row=14, column=0, columnspan=5)
        self.path_entry.bind("<Key>", self.getpath)

        self.path_entry.config(state='disabled')

        self.fullpath = ''

    def file(self):
        self.path_entry.config(state='normal')
        self._preview.update_output(otype='file')

    def line(self):
        self.path_entry.config(state='disabled')
        self._preview.update_output(otype='line')

    def getpath(self, event):
        self.fullpath = self.path_entry.get()

        self._preview.update_output(otype='file', path=self.fullpath)

        if event.keycode != 17:
            pyautogui.press('ctrl')


# Output
class Output:

    def __init__(self, _root):
        self._root = _root
        self._preview = _preview

        self.stroutput = tk.StringVar()
        self.stroutput.set('Output')
        self.ouputlabel = tk.Label(self._root, textvariable=self.stroutput, relief=tk.FLAT)
        self.ouputlabel.config(font=('Veranda', 11, 'bold'))
        self.ouputlabel.grid(pady=10, row=16, column=0, columnspan=5)

        self.b_file = tk.Button(self._root, text='Encrypt/Decrypt', width=47, relief='groove', bg='#d3d3d3',
                                command=self.callinterpreter).grid(row=17, column=0, columnspan=5)

    def callinterpreter(self):

        if self._preview.ret_()[1] == '-oto=line':
            var = subprocess.check_output("interpreter " + self._preview.ret_()[0], **subprocess_args(False))
            self._preview.get_output(str(var).lstrip("b'").lstrip('"').rstrip(r"\r\n'").rstrip(r'\r\n"'))

        elif self._preview.ret_()[1] == '-oto=file':
            subprocess.call("interpreter " + self._preview.ret_()[0])
            self._preview.get_output('')


# -- NOT MY CODE - NOT MY CODE - NOT MY CODE - NOT MY CODE - NOT MY CODE - NOT MY CODE - NOT MY CODE - NOT MY CODE -- #
# ------------------------ https://github.com/pyinstaller/pyinstaller/wiki/Recipe-subprocess ------------------------ #

# Create a set of arguments which make a ``subprocess.Popen`` (and
# variants) call work with or without Pyinstaller, ``--noconsole`` or
# not, on Windows and Linux. Typical use::
#
#   subprocess.call(['program_to_run', 'arg_1'], **subprocess_args())
#
# When calling ``check_output``::
#
#   subprocess.check_output(['program_to_run', 'arg_1'],
#                           **subprocess_args(False))
def subprocess_args(include_stdout=True):
    # The following is true only on Windows.
    if hasattr(subprocess, 'STARTUPINFO'):
        # On Windows, subprocess calls will pop up a command window by default
        # when run from Pyinstaller with the ``--noconsole`` option. Avoid this
        # distraction.
        si = subprocess.STARTUPINFO()
        si.dwFlags |= subprocess.STARTF_USESHOWWINDOW
        # Windows doesn't search the path by default. Pass it an environment so
        # it will.
        env = os.environ
    else:
        si = None
        env = None

    # ``subprocess.check_output`` doesn't allow specifying ``stdout``::
    #
    #   Traceback (most recent call last):
    #     File "test_subprocess.py", line 58, in <module>
    #       **subprocess_args(stdout=None))
    #     File "C:\Python27\lib\subprocess.py", line 567, in check_output
    #       raise ValueError('stdout argument not allowed, it will be overridden.')
    #   ValueError: stdout argument not allowed, it will be overridden.
    #
    # So, add it only if it's needed.
    if include_stdout:
        ret = {'stdout': subprocess.PIPE}
    else:
        ret = {}

    # On Windows, running this from the binary produced by Pyinstaller
    # with the ``--noconsole`` option requires redirecting everything
    # (stdin, stdout, stderr) to avoid an OSError exception
    # "[Error 6] the handle is invalid."
    ret.update({'stdin': subprocess.PIPE,
                'stderr': subprocess.PIPE,
                'startupinfo': si,
                'env': env})
    return ret
# -- NOT MY CODE - NOT MY CODE - NOT MY CODE - NOT MY CODE - NOT MY CODE - NOT MY CODE - NOT MY CODE - NOT MY CODE -- #


def about_window():

    about_win = tk.Toplevel()
    about_win.wm_title('About Encrypter...')

    about_win.geometry('404x210')
    about_win.resizable(0, 0)

    logoimg = tk.PhotoImage(file="logoimg.png")

    a_outputtitleimg = tk.Label(about_win, image=logoimg)
    a_outputtitleimg.photo = logoimg
    a_outputtitleimg.grid(row=0, rowspan=2)

    a_title = tk.StringVar()
    a_title.set('FTP Encrypter [Version ' + get_version() + '] by Andrew Woo (c) 2018')
    a_outtitle = tk.Label(about_win, textvariable=a_title)
    a_outtitle.grid(row=2)

    a_email = tk.StringVar()
    a_email.set('Email: seungminleader@gmail.com')
    a_outemail = tk.Label(about_win, textvariable=a_email)
    a_outemail.grid(row=4)

    a_web = tk.StringVar()
    a_web.set('Website: flamingthanatos.github.io')
    a_outweb = tk.Label(about_win, textvariable=a_web)
    a_outweb.grid(row=5)

    a_purpose = tk.StringVar()
    a_purpose.set('\nEncrypter is a Text Encryption program. Encrypter should not be used to \n'
                  'hide sensitive and important information. I am not responsible for your \n'
                  'actions. This Program is licensed under the MIT License.')
    a_outpurpose = tk.Label(about_win, textvariable=a_purpose)
    a_outpurpose.grid(row=7, rowspan=2)


def get_version():

    with open('version.txt', 'r') as v:
        version = v.readline()

    return version


if __name__ == '__main__':
    # Setup
    root = tk.Tk()
    root.title("Encrypter")
    root.iconbitmap("encico.ico")

    root.geometry('350x515')
    root.resizable(0, 0)

    # Setup _ Menu
    menubar = tk.Menu(root)

    filemenu = tk.Menu(menubar, tearoff=0)
    filemenu.add_command(label="Exit", command=root.quit)
    menubar.add_cascade(label="File", menu=filemenu)

    about_menu = tk.Menu(menubar, tearoff=0)
    about_menu.add_command(label="About", command=about_window)
    menubar.add_cascade(label="Help", menu=about_menu)

    root.config(menu=menubar)

    _preview = Preview(root)
    _preview.update()

    _step1 = Step1(root, _preview)
    _step2 = Step2(root, _preview)
    _step3 = Step3(root, _preview)
    _step4 = Step4(root, _preview)
    _step5 = Step5(root, _preview)

    _output = Output(root)

    root.mainloop()
