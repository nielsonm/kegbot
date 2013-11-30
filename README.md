#OpenSourcery KegBot
The following is a brain dump by me (@nielsonm) following a marathon Code Rally brainstorm with @ghyspran on the functionality and technologies surrounding the construction of a kegbot for OpenSourcery.

## Hardware
Raspberry Pi

Arduino

2x16 char display


## Software
Operating code mostly in Python

Data in MongoDB

WEB UI in Node


## Plan
### Phase I - Percentage to empty calculation
* Variables -# of meter "clicks" in a keg
OUTPUT to small display for local use.

OUTPUT to Mongo DB for use in phase II.

### Phase II - Web Interface
Build Node.js program to query db

Create web interface to display % to empty

### Phase III - Tracking & Metrics
Past beer popularity
* Time to empty
    * [%]/day
* Add graphing library (gCharts) to WEB.

### Phase IV - Metadata
* Type
* IBU
* ABV
* OG
* ??
* Brewer

OUTPUT in a YML file to be parsed to WEB.

### Phase V - Upcoming
Upcoming beers in queue.

### Phase VI - Social Media
* IRC bot
* Twitter bot
    * Current beers on tap
    * About
    * Favorite beer
