# RAN Packet Parser

A high-performance, memory-safe data ingestion engine designed to process and demultiplex raw telecommunications log streams.

## The Problem
Radio Access Network (RAN) equipment generates high-velocity, unstructured log data. Processing this data efficiently while maintaining system stability (avoiding memory leaks and crashes on malformed inputs) is critical for network monitoring.

## The Solution
This tool provides a robust parsing layer built with Modern C++17. It transforms raw log lines into structured `RanPacket` objects, utilizing:

- **Zero-Copy Semantics:** Uses `std::string_view` for high-performance substring operations without memory allocation.
- **Resource Management (RAII):** Utilizes `std::unique_ptr` to ensure strict ownership and zero memory leaks.
- **Defensive Programming:** Implements rigorous input validation and `std::optional` to handle partial or corrupted data gracefully.
- **Strict Parsing:** Utilizes `std::from_chars` logic via `std::stoull` with boundary checks to ensure data integrity.

## Architecture
1. **Parser Layer:** Filters noise and converts unstructured strings into typed objects.
2. **Validation Layer:** Enforces strict numeric and structural compliance.
3. **Queue System:** Separates healthy traffic from faulty logs for automated post-mortem analysis.