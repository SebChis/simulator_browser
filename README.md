# Web Browser Simulator

**Author:** Sebastian Chiselita

## 1. Project Overview
This project is a command-line Web Browser Simulator implemented entirely in C. It replicates core browser functionalities, including dynamic tab management, page rendering, and forward/backward history tracking, by heavily utilizing custom data structures and manual memory management.

## 2. Data Structures & Architecture
To ensure efficient navigation and resource management, the simulator avoids standard library containers and implements custom, optimized data structures via `typedef` structs:

* **Tab Management (Circular Doubly Linked List):** The open browser tabs are managed using a circular doubly linked list. This allows seamless `NEXT` and `PREV` traversal across tabs, wrapping around the ends of the tab bar.
* **History Tracking (Linked-List Stacks):** Each individual tab maintains its own isolated state, including two separate linked-list-based Stacks to handle the `BACKWARD` and `FORWARD` page history navigation.

## 3. Core Implementation Details

### The Engine (`main.c`)
Acts as the central orchestrator of the simulator:
* Bootstraps the environment (`init_browser`).
* Parses and loads the available web pages from the input file (`read_pages`).
* Acts as the main event loop, reading user commands and dispatching them to the underlying data structures.
* Safely deallocates all dynamic memory upon termination to ensure zero memory leaks.

### Memory & Page Management
To optimize memory usage, pages are not needlessly duplicated:
* **Default Page:** Whenever a `NEW_TAB` is created, a default blank page (ID = 0) is dynamically allocated specifically for that tab.
* **Shared Pages:** All other navigable pages are pre-loaded into a global page array. Tabs simply hold memory pointers referencing this array.
* **Garbage Collection:** Because of this shared-memory approach, specific teardown functions (e.g., `free_page_id_zero`) were implemented to exclusively free the dynamically allocated default pages without corrupting the global page array.

## 4. Supported Commands Engine

The simulator processes two primary categories of commands:

**Tab Operations:**
* `NEW_TAB` - Allocates and appends a new tab.
* `CLOSE` - Destroys the current tab and frees its local history.
* `OPEN <ID>` - Opens a specific tab index.
* `NEXT` / `PREV` - Cycles through the circular tab list.
* `PRINT` - Displays the current tab's status.

**Navigation Operations:**
* `PAGE <ID>` - Renders a new page in the current tab, pushing the previous state to the backward history stack.
* `BACKWARD` / `FORWARD` - Pops states from the respective history stacks to navigate time.
* `PRINT_HISTORY <ID>` - Dumps the chronological navigation stack of a specific tab.
