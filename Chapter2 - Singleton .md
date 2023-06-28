# The problem

## Write error log to file:

```
with open("flename.log", "a") as log_fle:
    log_fle.write("Log message goes here.\n")
```

Your log file is like a black box on an aircraft: it keeps a tally of your program’s execution. When your program crashes, you can pop open the black box and see what happened leading up to the crash, as well as where you should start looking for a bug. 

```
def log_message(msg):
    with open("flename.log", "a") as log_fle:
        log_fle.write("{0}\n".format(msg))
```
You can use this replacement for print statements wherever you want to record some state of your program for later review:
``` log_message("save this for later")```

One way of making the code a bit more user-friendly is to have a file in your project that contains nothing but the logging function. This allows you to import the logging function into any file in your project. All changes to the way logging is done in the project need only be made in this one file.
```
# logger.py
def log_message(msg):
    with open("/var/log/flename.log", "a") as log_fle:
        log_fle.write("{0}\n".format(msg))
```

```
# main_script.py
import logger
for i in range(4):
    logger.log_message("log message {}".format(i))
```

## Handle mutiple levels 

- Critical
- Error
- Warning
- Info
- Debug

In the log file, we want each message to be prepended with the level associated with the message. This helps us easily scan the file for specific types of messages. 

```
# logger.py
def critical(msg):
    with open("/var/log/flename.log", "a") as log_fle:
        log_fle.write("[CRITICAL] {0}\n".format(msg))

def error(msg):
    with open("/var/log/flename.log", "a") as log_fle:
        log_fle.write("[ERROR] {0}\n".format(msg))

def warn(msg):
    with open("/var/log/flename.log", "a") as log_fle:
        log_fle.write("[WARN] {0}\n".format(msg))

def info(msg):
    with open("/var/log/flename.log", "a") as log_fle:
        log_fle.write("[INFO] {0}\n".format(msg))

def debug(msg):
    with open("/var/log/flename.log", "a") as log_fle:
        log_fle.write("[DEBUG] {0}\n".format(msg))
```

```
# test_error_log.py
import logger
try:
    a = 1 / 0
except:
    logger.error("something went wrong")
```

In each of the repeated functions, the prefix was the only thing that differed from function to function. So, if we were to write a function that takes the message and level as parameters, we could use this function in each of the other functions and reduce it to a single line of code in each case. 
We now have a shorter, clearer logger to use in our other projects.

```
def write_log(level, msg):
    with open("/var/log/flename.log", "a") as log_fle:
        log_fle.write("[{0}] {1}\n".format(level, msg))
def critical(msg):
    write_log("CRITICAL",msg)
def error(msg):
    write_log("ERROR", msg)
def warn(msg):
    write_log("WARN", msg)
def info(msg):
    write_log("INFO", msg)
def debug(msg):
    write_log("DEBUG", msg)
```
# Enter the Object

Thinking about data and the functions that alter the data as a single entity is the basis for object-oriented programming.

```
class Logger(object):
    """A file-based message logger with the following properties
    
    Attributes:
        file_name: a string representing the full path of the log file to which this logger will write its messages
    """

    def __init__(self, file_name):
        """Return a Logger object whose file_name is *file_name*"""
        self.file_name = file_name

    def _write_log(self, level, msg):
        """Writes a message to the file_name for a specific Logger instance"""
        with open(self.file_name, "a") as log_file:
            log_file.write("[{0}] {1}\n".format(level, msg))

    def critical(self, level, msg):
        self._write_log("CRITICAL", msg)

    def error(self, level, msg):
        self._write_log("ERROR", msg)

    def warn(self, level, msg):
        self._write_log("WARN", msg)

    def info(self, level, msg):
        self._write_log("INFO", msg)

    def debug(self, level, msg):
        self._write_log("DEBUG", msg)
```

# Cleaning It Up

Now, you probably do not want to write to a unique log file for every part of your project that needs to write some log messages. So, what you want is some way to get the same logger that you already created if there is one, or create a new logger if none already exist.
We do that by taking control of the process by which the logger object is created. 

```
# singleton_object.py
class SingletonObject(object):
    class __SingletonObject():
        def __init__(self):
            self.val = None

        def __str__(self):
            return "{0!r} {1}".format(self, self.val)

    instance = None

    def __new__(cls):
        if not SingletonObject.instance:
            SingletonObject.instance = SingletonObject.__SingletonObject()
        return SingletonObject.instance

    def __getattr__(self, name):
        return getattr(self.instance, name)

    def __setattr__(self, name):
        return setattr(self.instance, name)
```

### Private Class: 
The `SingletonObject` class contains a private class called `__SingletonObject`. The leading underscores indicate that it's intended to be a private class, not to be used outside the SingletonObject class. This private class represents the actual implementation of the logger.

### Private Class Attributes and Methods: 
The private class (`__SingletonObject`) has an object attribute called "`val`" and two methods: `init` for initializing the object and `str` for providing a string representation of the object (used in print statements).

### Class Attribute: 
The `SingletonObject` class has a class attribute called "`instance`" which is initially set to `None`. This attribute is used to keep track of the singleton instance.

### `new` Method: 
The `new` method is a class method that overrides the default behavior of object creation. It receives the class (`cls`) as a parameter instead of the instance (`self`). It checks if an instance of the `SingletonObject` already exists (by checking if the instance class variable is `None`). If no instance exists, it creates a new instance of the private class (`__SingletonObject`) and assigns it to the instance class variable. Finally, it returns the instance.

### `getattr` Method: 
The `getattr` method is invoked when an attribute is accessed but not found in the `SingletonObject` class itself. It relays the attribute access to the corresponding attribute in the instance class variable, allowing the outer object to behave as if it has those attributes.

### `setattr` Method: 
The `setattr` method is invoked when an attribute is set in the `SingletonObject` class. It relays the attribute assignment to the instance class variable, ensuring that the attribute is set on the object housed in the instance variable.

In summary, the code sets up a Singleton pattern where only one instance of the private class (`__SingletonObject`) can exist. The `SingletonObject` class acts as a proxy, relaying attribute access and assignment to the instance class variable, providing a unified interface for interacting with the singleton object.

```
# test_singleton.py
from singleton_object import SingletonObject

obj1 = SingletonObject()
obj1.val = "Object value 1"
print("print obj1: ", obj1)
print("-----")
obj2 = SingletonObject()
obj2.val = "Object value 2"
print("print obj1: ", obj1)
print("print obj2: ", obj2)

```
Here is output
```
print obj1: <__main__.SingletonObject.__SingletonObject object at
0x7fda5524def0> Object value 1
-----
print obj1: <__main__.SingletonObject.__SingletonObject object at
0x7fda5524def0> Object value 2
print obj2: <__main__.SingletonObject.__SingletonObject object at
0x7fda5524def0> Object value 2
```