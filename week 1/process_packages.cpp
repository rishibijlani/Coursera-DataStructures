#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    Response Process(const Request &request) {
        // write your code here

        while(!finish_time_.empty() && finish_time_.front() <= request.arrival_time)
          finish_time_.pop();

        if(finish_time_.size() == size_)
          return Response(true, -1);                         //returns shit to response as dropped

        int start_time = finish_time_.empty() ? request.arrival_time : finish_time_.back();

        finish_time_.push(start_time+request.process_time);

        return Response(false, start_time);


        // we get arrival time and process time here
        //return(dropped bool, -1 or start time)


//queue.pop elements WHERE packet.finish_time <= newPacket.arrival_time
//if(buffer.isFull) -> return(true, -1) ELSE queue.push(finish_time)       [finish_time=start+processing]
// finish_time = start+processing;      start=0(immediate if queue empty AF) || last finish time in Q



/*
 store in the list or queue finish_time the times when the computer will
finish processing the packets which are currently stored in the network buffer, in increasing order. When
a new packet arrives, you will first need to pop from the front of finish_time all the packets which are
already processed by the time new packet arrives. Then you try to add the finish time for the new packet in
finish_time. If the buffer is full (there are already 𝑆 finish times in finish_time), the packet is dropped.
Otherwise, its processing finish time is added to finish_time.

If finish_time is empty when a new packet arrives, computer will start processing the new packet
immediately as soon as it arrives. Otherwise, computer will start processing the new packet as soon as it
finishes to process the last of the packets currently in finish_time (here is when you need to access the
last element of finish_time to determine when the computer will start to process the new packet). You will
also need to compute the processing finish time by adding 𝑃𝑖 to the processing start time and push it to the
back of finish_time.
*/


    }
private:
    int size_;
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
