# ESP32 Global Weather Analytics Dashboard

A modern IoT weather dashboard built using ESP32, Arduino IDE, and Open-Meteo APIs. The project allows users to search for any city worldwide and view real-time weather information, 7-day forecasts, interactive charts, and additional weather insights through a responsive web interface hosted directly on the ESP32.

## Features

* Search weather for any city in the world
* Real-time temperature monitoring
* Humidity tracking
* Wind speed information
* Sunrise and sunset timings
* 7-day weather forecast
* Interactive temperature chart
* Interactive humidity chart
* Mobile-friendly responsive dashboard
* EEPROM storage for last searched city
* No API key required
* Hosted directly on ESP32

## Technology Stack

* ESP32
* Arduino IDE
* HTML
* CSS
* JavaScript
* Chart.js
* Open-Meteo API
* REST APIs
* JSON Parsing
* EEPROM Storage

## Project Architecture

```text
User Browser
      │
      ▼
ESP32 Web Server
      │
      ├── Open-Meteo Geocoding API
      │       │
      │       ▼
      │  Latitude & Longitude
      │
      └── Open-Meteo Weather API
              │
              ▼
      Real-Time Weather Data
              │
              ▼
      Interactive Dashboard
```

## Dashboard Features

### Current Weather

* Temperature
* Humidity
* Wind Speed
* Weather Conditions

### Forecast Information

* 7-Day Temperature Forecast
* Sunrise Time
* Sunset Time

### Data Visualization

* Temperature Trend Chart
* Humidity Trend Chart

## Hardware Requirements

* ESP32 Development Board
* Wi-Fi Connection
* USB Cable

## Software Requirements

* Arduino IDE
* ArduinoJson Library

## Example Usage

Search for:

* London
* Tokyo
* New York
* Paris
* Sydney
* New Delhi

The dashboard will instantly display current weather and forecast information.

## Future Enhancements

* Air Quality Index (AQI)
* Weather Alerts
* GPS-based Location Detection
* Historical Weather Analytics
* Data Logging
* Weather Map Integration
* Multi-City Comparison
* Progressive Web App (PWA)
* Cloud Database Integration

## Learning Outcomes

This project demonstrates:

* IoT Development
* Embedded Web Servers
* API Integration
* Real-Time Data Processing
* Frontend Dashboard Development
* Data Visualization
* ESP32 Programming
* JSON Parsing
* Responsive Web Design

## License

This project is open-source and available under the MIT License.
