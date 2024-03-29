# liblogger

[![Build Status](https://travis-ci.org/briandowns/liblogger.svg?branch=master)](https://travis-ci.org/briandowns/liblogger)

liblogger is a simple JSON logger in C.

## Use

To use this single-header library, call the `log` macro. This macro takes a log level, any number of `log_field_t` pointers containing a string key and a log value. 

The supported int values are:  `int`, `int8`, `int16`, `int32`, `int64`
The supported uint values are: `uint`, `uint8`, `uint16`, `uint32`, `uint64`

As well as `double`, and `string`.

The supported log levels are: `trace`, `debug`, `info`, `warn`, `error`, `fatal`, 

For a successful log entry to be made, a key and a value need to be provided. If no value is provided, that field will not be logged.

## Example 

Build the example:

```
make example
```

```c
#include <stdio.h>

#include "logger.h"

int
main(int argc, char **argv)
{
    log_init(stdout);
    log(log_INFO, 
        log_string("msg", "records added successfully"), 
        log_uint8("count", 2));
    log(log_INFO, 
        log_string("msg", "records added successfully"), 
        log_int64("count", 9223372036854775807));
    log(log_INFO, 
        log_string("msg", "records added partially"), 
        log_double("count", 3.14));
    log(log_INFO, 
        log_string("msg", "record added successfully"), 
        log_string("name", "Brian"), 
        log_double("elapsed", 5.76)); 
}
```

Expected output:

```sh
{ "timestamp": 1541620673, "level": "info", "msg": "records added successfully", "count": 2 }
{ "timestamp": 1541620673, "level": "info", "msg": "records added successfully", "count": 9223372036854775807 }
{ "timestamp": 1541620673, "level": "info", "msg": "records added partially", "count": 3 }
{ "timestamp": 1541620673, "level": "info", "msg": "record added successfully", "name": "Brian", "elapsed": 5.7599999999999998 }
```

Write to a log file:

```c
FILE *f = fopen("file.log", "w");
log_init(f);
log(log_INFO, log_string("msg", "records added successfully"), log_uint8("count", 2));
fclose(f);
```

## Requirements

* [json-c](https://github.com/json-c/json-c)

Lots of thanks to [Ayan George](https://github.com/ayang64) for the help with getting this where it is.

## Contact

Brian Downs [@bdowns328](http://twitter.com/bdowns328)

## License

BSD 2 Clause [License](/LICENSE).
