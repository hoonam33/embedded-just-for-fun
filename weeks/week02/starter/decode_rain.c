int *decode_rain(const char bytes[]) {
    int rain = bytes[0] | (bytes[1] << 8);
    return &rain;
}
