format:

```json
{
	"window": {
		"size": [80, 80],
		"background-color": [40, 40, 40],
		"font-path": "Roboto-Regular.ttf",
		"font-size": 42 // When not present it'll default to 32
	},

	"keys": [
		{
			"code": 65, // key code because i couldnt get string names to work
			"before": {
				"rect": [0, 0, 80, 80], // x, y, w, h
				"background-color": [0, 0, 0], // r, g, b
				"label-content": "test", // When not present, defaults to " ".
				"label-color": [255, 255, 255] // r, g, b
			},
			// "after" only includes the properties that change on press
			"after": {
				"background-color": [255, 255, 255],
				"label-color": [0, 0, 0]		
			}
		}
	]
}
```
comments in json idc

dont look into layoutParser.cpp
