import configparser
from unipath import Path

BASE_DIR = Path(__file__).ancestor(2)
DATA_DIR = BASE_DIR.child("data")

class Init:
    '''Init:  

    '''
    def WriteConfig(self):
        # lets create that config file for next time...
        cfgfile = open(BASE_DIR.child("config.ini"),'w')

        # Add content to the file
        Config = configparser.ConfigParser()
        Config.add_section('File')
        Config.set('File', 'path', DATA_DIR.child("filename.vtu"))
        Config.add_section('Geometry')
        Config.set('Geometry', 'dimension', "2")
        Config.add_section('Mesh')
        Config.add_section('Material')
        Config.add_section('Source')
        Config.add_section('Boundary')
        Config.write(cfgfile)
        cfgfile.close()

    def ConfigSectionMap(self):
        Config = configparser.ConfigParser()
        Config.read(BASE_DIR.child("config.ini"))
        section = Config.sections()[0]
        dict1 = {}
        options = Config.options(section)
        for option in options:
            try:
                dict1[option] = Config.get(section, option)
                if dict1[option] == -1:
                    DebugPrint("skip: %s" % option)
            except:
                print("exception on %s!" % option)
                dict1[option] = None
        return dict1