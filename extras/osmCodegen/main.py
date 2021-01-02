import tkinter
from tkinter import filedialog
import xml.etree.ElementTree as ET
import re

class PathHandler:
    def __init__(self):
        self.path = False

osmPath = PathHandler()

class IDManager:
    def __init__(self):
        self.idList = []

    def get(self, id):
        if id not in self.idList:
            self.idList.append(id)
        return str(self.idList.index(id));

nodeIDManager = IDManager()

class XMLDesiredChild:

    def __init__(self, tag, attributes):
        self.tag = tag
        self.attributes = attributes

    def compare(self, child, end = True):
        if self.tag == child.tag:
            childStr = '<' + self.tag
            for attrib in self.attributes:
                try:
                    value = child.attrib[attrib]
                    if attrib == "id" or attrib == "ref":
                        value = nodeIDManager.get(value)
                    childStr += ' ' + attrib + '="' + value + '"'
                except:
                    pass
            if end:
                childStr += '/>'
            else:
                childStr += '>'

            return childStr
        else:
            return False

def load():
    filedata = filedialog.askopenfile(filetypes = [("OSM files", "*.osm")])
    if filedata is not None:
        osmPath.path = filedata.name
    else:
        osmPath.path = False

    filedata.close()
    print(osmPath.path)

def save():
    print(osmPath.path)
    filePath = filedialog.asksaveasfile(filetypes = [("C/C++ header files", "*.h")])
    path = filePath.name
    filePath.close()
    print(osmPath.path)

    if osmPath.path:
        writeHeaderFile(osmPath.path, path)

def writeHeaderFile(osmFilePath, headerFilePath):

    map = ET.parse(osmFilePath)
    root = map.getroot()

    desiredChilds = []
    desiredChilds.append(XMLDesiredChild('node', ['id', 'lat', 'lon']))
    if waysEn.get():
        desiredChilds.append(XMLDesiredChild('way', ['id']))
        desiredChilds.append(XMLDesiredChild('nd', ['ref']))

    outputStr = '<osm>'
    for child in root:
        end = True
        subStr = ""
        valid = False

        for desiredChild in desiredChilds:
            childroot = list(child.iter())

            if len(childroot) > 1:
                end = False

            iteration = 0;

            for subchild in childroot:
                if iteration == 0:
                    result = desiredChild.compare(subchild, end)
                else:
                    result = desiredChild.compare(subchild)

                if result:
                    if iteration > 0:
                        valid = True
                    subStr += result
                iteration += 1

        if not end:
           subStr += '</' + child.tag + '>'

        if end or valid:
            outputStr += subStr

    outputStr += '</osm>'
    outputStr = re.sub('"', "'", outputStr)

    splt = headerFilePath.split("/")
    name = re.sub('\.', '_', splt[len(splt) - 1]);

    file = open(headerFilePath, "w")
    file.writelines(['#ifndef ' + name.upper() + '\n',
                    '#define ' + name.upper() + '\n',
                    'const char ' + re.sub('_h', '', name).lower() + '[] = "' + outputStr + '";\n',
                    '#endif'])
    file.close()

main = tkinter.Tk()

waysEn = tkinter.BooleanVar()

main.title("OSM code generator")
main.geometry("620x270")
main.grid_rowconfigure(3, minsize = 100)

loadButton = tkinter.Button(main, text = "Load osm", command = load)
loadButton["width"] = 75
loadButton["height"] = 5
loadButton.grid(row = 0)

waysCb = tkinter.Checkbutton(main, text = "Ways", variable = waysEn, onvalue = True, offvalue = False)
waysCb.grid(row = 1)

saveButton = tkinter.Button(main, text = "Generate code", command = save)
saveButton["width"] = 75
saveButton["height"] = 5
saveButton.grid(row = 2)

main.mainloop()


