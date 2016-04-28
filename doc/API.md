# Lamp-REST API
## Response structure
### No Error
```json
{
    "status": true,
    "data": [
        {"id": 1}
    ]
}
```
### Error
```json
{
    "status": false,
    "message": "Invalid path: /Lamp/On/foo instead of /Lamp/On"
}
```
## Turn The Lamp ON in Interval
Trun the lamp on for specific interval

- URL
: /Lamp/OnI

- Method
: `POST`

- JSON params
:

    | Parameter |   Value  |              Description               |
    |:---------:|:--------:|:-------------------------------------- |
    |  interval |  integer | Duration the lamp is turned on         |

- Success response
: Code: 200

- Error response
:

    |   Status codes       |              Description               |
    |:--------------------:|:-------------------------------------- |
    |  400 Bad Request     | The specified parameters are not valid |
    |  404 Not Found       | The specified path was not found       |
    |  501 Not Implemented | The specified method was not valid     |

## Turn The Lamp On
Trun the lamp on

- URL
: /Lamp/On

- Method
: `POST`

- JSON params
:

    | Parameter |   Value  |              Description               |
    |:---------:|:--------:|:-------------------------------------- |
    |     id    |  integer | Target lamp identificaiton             |

- Success response
: Code: 200

- Error response
:

    |   Status codes       |              Description               |
    |:--------------------:|:-------------------------------------- |
    |  400 Bad Request     | The specified parameters are not valid |
    |  404 Not Found       | The specified path was not found       |
    |  501 Not Implemented | The specified method was not valid     |

## Turn The Lamp OFF
Trun the lamp off

- URL
: /Lamp/Off

- Method
: `POST`

- JSON params
:

    | Parameter |   Value  |              Description               |
    |:---------:|:--------:|:-------------------------------------- |
    |     id    |  integer | Target lamp identificaiton             |

- Success response
: Code: 200

- Error response
:

    |   Status codes       |              Description               |
    |:--------------------:|:-------------------------------------- |
    |  400 Bad Request     | The specified parameters are not valid |
    |  404 Not Found       | The specified path was not found       |
    |  501 Not Implemented | The specified method was not valid     |


## List The Lamps :)
Return list of the avaible sink of lamps event.

- URL
: /Lamp/List

- Method
: `POST`

- JSON params
: None

- Success response
:
    - Code: 200
    - Body:
    ```json
[{"id":"19 1b 9e e8 6e db f9 a2 9f cc 5e 32 74 ac f0 f6 5c 84 8b cd "}]
    ```

- Error response
:
		
    |   Status codes       |              Description               |
    |:--------------------:|:-------------------------------------- |
    |  400 Bad Request     | The specified parameters are not valid |
    |  404 Not Found       | The specified path was not found       |
    |  501 Not Implemented | The specified method was not valid     |

