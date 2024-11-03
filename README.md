# liblogger

liblogger is a structured logger for C/C++. The output format is JSON. liblogger supports writing to stdout, stderr, and to a given file.

## Usage

To use this library, initialize the logger with `s_log_init()` and call the `s_log` macro. The latter macro takes a log level, any number of `s_log_field_t` pointers containing a string key and a log value. 

The supported int values are:  `int`, `int8`, `int16`, `int32`, `int64`
The supported uint values are: `uint`, `uint8`, `uint16`, `uint32`, `uint64`
And`double`, and `string`.

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
    s_log_init(stdout); 
    s_log(S_LOG_INFO, 
        s_log_string("msg", "records added successfully"),
        s_log_uint("count", 2));
    s_log(S_LOG_INFO, 
        s_log_string("msg", "records added successfully"),
        s_log_int64("count", 9223372036854775807));
    s_log(S_LOG_INFO, 
        s_log_string("msg", "record added successfully"),
        s_log_string("name", "Brian"),
        s_log_double("elapsed", 5.76));
    s_log(S_LOG_FATAL, s_log_string("msg", "dead :("));  
}
```

Expected output:

```sh
{ "timestamp": 1541620673, "level": "info", "msg": "records added successfully", "count": 2 }
{ "timestamp": 1541620673, "level": "info", "msg": "records added successfully", "count": 9223372036854775807 }
{ "timestamp": 1541620673, "level": "info", "msg": "records added partially", "count": 3 }
{ "timestamp": 1541620673, "level": "info", "msg": "record added successfully", "name": "Brian", "elapsed": 5.75 }
```

Write to a log file:

```c
FILE *f = fopen("file.log", "w");
s_log_init(f);
s_log(S_LOG_INFO,
    s_log_string("msg", "records added successfully"),
    s_log_uint8("count", 2));
fclose(f);
```

## Requirements / Dependencies

* [jansson](https://github.com/akheron/jansson)

A lot of thanks to [Ayan George](https://github.com/ayang64) for the help with getting this where it is.

## Contact

Brian Downs [@bdowns328](http://twitter.com/bdowns328)

## License

BSD 2 Clause [License](/LICENSE).
