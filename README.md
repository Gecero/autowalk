# autowalk
a tool similar to binwalk that detects data in files but also extracts it

##### Table of Contents  
[Usage](#usage)  
[Autowalk compared to Binwalk](#comparison)  
[To-Do](#todo)  

<a name="usage"/>

# Usage
![](https://youtube.alpmann.de/img/autowalk-usage.gif "autowalk usage example gif")

| Usage: | autowalk [OPTIONS] [FILE]       |
|--------|---------------------------------|
| -x     | dont extract data after parsing |
| -q     | dont write debug/info output    |
| -h     | write help message              |

<a name="comparison">
  
# Autowalk compared to Binwalk
| Why autowalk's better                  | Why autowalk's worse                                   |
|----------------------------------------|--------------------------------------------------------|
| autowalk is focused on data extraction | very slow                                              |
| written in c++                         | sometimes no detection where binwalk detects something |
| small codebase                         | needs internet connection to setup build dependencies  |

<a name="todo">

# To-Do
- Add Regex Detection (similar to binwalk - example output: "foo copyright string foo")
- Maybe add a graph where data is located and how big it is (similar to windirstat)
- Increase analysing speed
- Add more routine for more data types in handleData()
- More filters
