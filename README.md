
# StraightWeather | The Bowling Boys
## By: Benjamin Adelman, Haden Anderson, Hudson Whitney
----------
## Summary:

This project utilizes two different data structures to access randomly accessed weather data as well as max/min/average weather data: a Hashmap and a Maxheap. The purpose of our project is to contrast the two data structures in different tasks to show how they differ in their ideal use cases, and to provide an easy-to-use terminal interface that lets the user access important weather data from various cities, listed below.

## List of Cities:
- Chicago
- Dallas
- Houston
- Los Angeles
- New York
- Philadelphia
- Phoenix
- San Antonio
- San Diego
- San Jose

## Weather Data Types:
- Temperature
- Humidity
- Precipitation
- Wind
----------
## File Descriptions:
- CSVLoader: Declares and implements a CSVLoader class that reads the weather data, filters rows by city and attribute, and inserts each timestamp/value pair into a the hashmap and heap
- Hashmap: Implements a hashmap with sorted linked lists of readings
- Heap: Implements a maxheap with nodes for datatime and corresponding value
- Main: Implements the user interface and prompts the user for input. Reports the chosen statistic from each data structure and its access times.
----------
## How to Run:
1. Clone the repository
2. Set the working directory to the main project folder with CSV data
3. Build and Run


