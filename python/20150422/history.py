from collections import defaultdict


class History:
    def __init__(self):
        self.history = defaultdict(list)

    
    def __getattr__(self,name):
        his_cnt = 0
        while name.endswith("_prev"):
            his_cnt += 1
            name = name[:-5]
        if name not in self.__dict__:
            raise NameError("'%s' is not an attribute of the class." % name)
        return self.__dict__[name] if his_cnt==0 else self.history[name][-his_cnt] if his_cnt<=len(self.history[name]) else None


    def __getitem__(self,index):
        if not isinstance(index, int) or index > 0:
            raise IndexError("'%s' is not allow." % str(index))
        ret = {}
        for key in self.__dict__:
            if key != "history":
                ret[key] = self.__getattr__(key + "_prev" * (-index))
        return ret

    
    def __setattr__(self,name,value):
        if name.find("_prev") >= 0:
            raise NameError("Attributes can not containing the string '_prev'")
        if name in self.__dict__:
            self.history[name].append(self.__dict__[name])
        object.__setattr__(self, name, value)




if __name__ == '__main__':
    # Put in simple tests for History before allowing driver to run

    print()
    import driver
    
    driver.default_file_name = 'bsc2.txt'
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
