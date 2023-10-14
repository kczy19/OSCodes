# OSCodes

## Usage

### Troubleshooting Response Time

If you encounter issues with the response time in this project, consider the following two options:

1. **Set Response Time to `currTime`**:
   - You can set the response time of a process to the current time (`currTime`) when the process starts executing.

2. **Set Response Time to `currTime - processes[index].arrival_time`**:
   - Alternatively, calculate the response time as the current time (`currTime`) minus the arrival time of the process (`processes[index].arrival_time`).

Please choose the method that best suits your specific use case and requirements.

## Contributing

Feel free to contribute to this project by submitting bug reports, feature requests, or code contributions. Follow our guidelines for coding standards and pull request submissions.

## License

This project is not licensed and is provided as-is. You are free to use, modify, and distribute it at your own discretion.


