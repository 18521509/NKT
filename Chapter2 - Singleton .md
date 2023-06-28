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

