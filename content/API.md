### Response structure
#### No Error
```json
{
    "status": true,
    "data": [
        {"id": 1}
    ]
}
```
#### Error
```json
{
    "status": false,
    "message": "Invalid path: /Lamp/On/foo instead of /Lamp/On"
}
```
### Turn The Lamp ON
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

### List The Lamps :)
Return list of the avaible sink of lamps event.

- URL
: /Lamp/List
