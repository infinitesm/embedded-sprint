#include "../minitest/minitest.h"
#include "cbuf.h"

// Test cases
// 1. init -> empty, not full
TEST_CASE(test_init) {
    CircularBuffer cb;
    cb_init(&cb, 4);
    TEST(ts, "empty after init", cb_is_empty(&cb));
    TEST(ts, "not full after init", !cb_is_full(&cb));
    TEST(ts, "size==0 after init", cb.size == 0);
    TEST(ts, "tail==0 after init", cb.tail == 0);
    cb_free(&cb);
}

// 2. enqueue until full, then reject next enqueue attempt
TEST_CASE(test_enqueue_until_full) {
    CircularBuffer cb;
    cb_init(&cb, 4);

    TEST(ts, "enq 10", cb_enqueue(&cb, 10));
    TEST(ts, "enq 20", cb_enqueue(&cb, 20));
    TEST(ts, "enq 30", cb_enqueue(&cb, 30));
    TEST(ts, "enq 40", cb_enqueue(&cb, 40));
    TEST(ts, "buffer full", cb_is_full(&cb));
    TEST(ts, "size == capacity", cb.size == cb.capacity);
    TEST(ts, "enq fails when full", !cb_enqueue(&cb, 50));
    cb_free(&cb);
}

// 3. dequeue until empty, then reject next dequeue attempt
TEST_CASE(test_dequeue_until_empty) {
    CircularBuffer cb;
    int capacity = 4;
    cb_init(&cb, capacity);

    // fill the buffer
    for (int i = 1; i <= capacity; i++) {
        cb_enqueue(&cb, i * 10);
    }

    // empty the buffer
    int out;
    TEST(ts, "dequeue 10", cb_dequeue(&cb, &out));
    TEST(ts, "out 10", out == 10);
    TEST(ts, "dequeue 20", cb_dequeue(&cb, &out));
    TEST(ts, "out 20", out == 20);
    TEST(ts, "dequeue 30", cb_dequeue(&cb, &out));
    TEST(ts, "out 30", out == 30);
    TEST(ts, "dequeue 40", cb_dequeue(&cb, &out));
    TEST(ts, "out 40", out == 40);


    // free the buffer
    cb_free(&cb);
}

// 4. wrap-around behavior, interleave enq/deq so head/tail cross array end
TEST_CASE(test_wrap_behavior) {
    CircularBuffer cb;
    cb_init(&cb, 4);
    int out;

    // push 3, pop 2 -> tail advances, room at front
    cb_enqueue(&cb, 10);
    cb_enqueue(&cb, 20);
    cb_enqueue(&cb, 30);
    cb_dequeue(&cb, &out); // 10
    cb_dequeue(&cb, &out); // 20

    // now enqueue more so head wraps
    cb_enqueue(&cb, 40);
    cb_enqueue(&cb, 50);   // should wrap here in typical mod arithmetic

    TEST(ts, "peek sees 30", ({ int v; cb_peek(&cb, &v) && v == 30; }));
    TEST(ts, "dequeue 30", cb_dequeue(&cb, &out));
    TEST(ts, "out 30", out == 30);
    TEST(ts, "dequeue 40", cb_dequeue(&cb, &out));
    TEST(ts, "out 40", out == 40);
    TEST(ts, "dequeue 50", cb_dequeue(&cb, &out));
    TEST(ts, "out 50", out == 50);

    // free the buffer
    cb_free(&cb);
}

// 5. peek independence, peek call should not change any buffer property
TEST_CASE(test_peek_independence) {
    CircularBuffer cb;
    cb_init(&cb, 4);
    cb_enqueue(&cb, 10);
    cb_enqueue(&cb, 20);
    cb_enqueue(&cb, 30);

    size_t head, tail, size;
    head = cb.head;
    tail = cb.tail;
    size = cb.size;

    int out;

    TEST(ts, "peek call", cb_peek(&cb, &out));
    TEST(ts, "out 10", out == 10);
    TEST(ts, "independence", cb.head == head && cb.tail == tail && cb.size == size);

    // free the buffer
    cb_free(&cb);
}

// 6. capacity==1 edge case (wraps every time)
TEST_CASE(test_wrap_edge_case) {
    CircularBuffer cb;
    cb_init(&cb, 1);
    int out;

    TEST(ts, "enqueue 10", cb_enqueue(&cb, 10));
    TEST(ts, "buffer full", cb_is_full(&cb));
    TEST(ts, "enqueue expected fail", !cb_enqueue(&cb, 20));
    TEST(ts, "dequeue 10", cb_dequeue(&cb, &out));
    TEST(ts, "out 10", out == 10);
    TEST(ts, "buffer empty", cb_is_empty(&cb));

    // free the buffer
    cb_free(&cb);
}

// 7. free buffer call leaves buffer in safe state
TEST_CASE(test_free_safety) {
    CircularBuffer cb;
    cb_init(&cb, 4);
    cb_free(&cb);

    TEST(ts, "buffer NULL", !cb.buffer);
    TEST(ts, "buffer size", cb.size == 0);
    TEST(ts, "buffer capacity", cb.capacity == 0);
}

// 8. full real-world sequence
TEST_CASE(test_full_sequence) {
    CircularBuffer cb;
    cb_init(&cb, 5);
    int out;

    // round 1
    cb_enqueue(&cb, 1);
    cb_enqueue(&cb, 2);
    cb_enqueue(&cb, 3);
    cb_dequeue(&cb, &out); // 1
    cb_enqueue(&cb, 4);
    cb_enqueue(&cb, 5);
    cb_enqueue(&cb, 6); // now full
    TEST(ts, "full after 6 enqueue and 1 dequeue", cb_is_full(&cb));

    // contents: 2,3,4,5
    cb_dequeue(&cb, &out);
    TEST(ts, "out 2", out == 2);
    cb_dequeue(&cb, &out);
    TEST(ts, "out 3", out == 3);

    cb_enqueue(&cb, 7);
    cb_enqueue(&cb, 8); // wrap
    // drain remaining: 4,5,6,7,8
    cb_dequeue(&cb, &out);
    TEST(ts, "out 4", out == 4);
    cb_dequeue(&cb, &out);
    TEST(ts, "out 5", out == 5);
    cb_dequeue(&cb, &out);
    TEST(ts, "out 6", out == 6);
    cb_dequeue(&cb, &out);
    TEST(ts, "out 7", out == 7);
    cb_dequeue(&cb, &out);
    TEST(ts, "out 8", out == 8);
    TEST(ts, "empty at end", cb_is_empty(&cb));

    cb_free(&cb);
}
int main() {
    const Test tests[] = {
        {"test_init", test_init},
        {"test_enqueue_until_full", test_enqueue_until_full},
        {"test_dequeue_until_empty", test_dequeue_until_empty},
        {"test_wrap_behavior", test_wrap_behavior},
        {"test_peek_independence", test_peek_independence},
        {"test_wrap_edge_case", test_wrap_edge_case},
        {"test_free_safety", test_free_safety},
        {"test_full_sequence", test_full_sequence}
    };
    return run_all_tests(tests, sizeof(tests) / sizeof(tests[0]));
}