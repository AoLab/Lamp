# Lamp-REST API
## Response structure
### No Error
```json
{
    "status": true,
    "data": { "Response Data OBJECT" }
}
```
### Error
```json
{
    "status": false,
    "message": "Error Message STRING"
}
```
## Turn The Lamp ON and OFF
Trun the lamp on and off

- URL
: /lamp/turn

- Method
: `POST`

- JSON params
:

    | Parameter |   Value  |              Description               |
    |:---------:|:--------:|:-------------------------------------- |
    |     id    |  string  | Target lamp identificaiton             |
    |   status  |  boolean | `true` for on and `false` for off      |

- Success response
: Code: 200

- Error response
:

    |   Status codes       |              Description               |
    |:--------------------:|:-------------------------------------- |
    |  400 Bad Request     | The specified parameters are not valid |
    |  404 Not Found       | The specified path was not found       |
    |  501 Not Implemented | The specified method was not valid     |

## Check The Lamp Status
Check the lamp status (is it on or off ?)

- URL
: /lamp/status

- Method
: `POST`

- JSON params
:

    | Parameter |   Value  |              Description               |
    |:---------:|:--------:|:-------------------------------------- |
    |     id    |  string  | Target lamp identificaiton             |

- Success response
: Code: 200

- Error response
:

    |   Status codes       |              Description               |
    |:--------------------:|:-------------------------------------- |
    |  400 Bad Request     | The specified parameters are not valid |
    |  404 Not Found       | The specified path was not found       |
    |  501 Not Implemented | The specified method was not valid     |
