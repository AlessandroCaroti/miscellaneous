from heapq import heapify, heappush, heappop


class PriorityQueue:

    def __init__(self):
        self.pq = []                         # list of entries arranged in a heap
        self.entry_finder = {}               # mapping of tasks to entries
        self.REMOVED = '<removed-task>'      # placeholder for a removed task
        self.counter = 0                     # unique sequence count

    def move_up(self, value, priority):
        'Add a new task or update the priority of an existing task'
        self.remove_task(value)  # mark as removed
        self.counter += 1
        entry = [priority, self.counter, value]
        self.entry_finder[value] = entry
        heappush(self.pq, entry)

    def insert(self, value, priority):
        'Add a new item to the priority queue'
        self.counter += 1
        entry = [priority, self.counter, value]
        self.entry_finder[value] = entry
        heappush(self.pq, entry)
    
    def add_or_update(self, value, priority):
        'Add a new item or update the priority of an existing task'
        if value in self.entry_finder:
            self.remove_task(value)
        self.counter += 1
        entry = [priority, self.counter, value]
        self.entry_finder[value] = entry
        heappush(self.pq, entry)

    def remove_task(self, value):
        'Mark an existing task as REMOVED.  Raise KeyError if not found.'
        entry = self.entry_finder.pop(value)
        entry[-1] = self.REMOVED

    def pop(self):
        'Remove and return the lowest priority task. Raise KeyError if empty.'
        while self.pq:
            priority, count, value = heappop(self.pq)
            if value is not self.REMOVED:
                del self.entry_finder[value]
                return value
        raise KeyError('pop from an empty priority queue')

    def not_empty(self):
        return bool(len(self.entry_finder))
