CXX = g++
CXXFLAGS = -Wall -std=c++17
SRCS = main.cpp Wallet.cpp OrderBook.cpp MerkelMain.cpp CSVreader.cpp OrderBookEntry.cpp
TARGET = app

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
