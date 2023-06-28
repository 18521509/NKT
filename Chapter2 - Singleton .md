# The problem
Write log to file:

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