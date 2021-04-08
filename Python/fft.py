import math
import cmath

def fft(signal):
    n = len(signal)
    if n == 1:
        return signal
    freq = cmath.exp(2 * cmath.pi * 1j / n)
    signal_even = [signal[i] for i in range(0, n, 2)]
    signal_odd = [signal[i] for i in range(1, n, 2)]
    y_even = fft(signal_even)
    y_odd = fft(signal_odd)
    y = [0] * n
    half_n = n//2
    for i in range(0, half_n):
        freq_j = freq ** i
        y[i] = y_even[i] + freq_j * y_odd[i]
        y[i + half_n] = y_even[i] - freq_j * y_odd[i]
    return y


if __name__ == "__main__":
    time = [i/256 for i in range(0,256)]
    signal = [math.sin(2*math.pi*2*t) for t in time]
    for f in fft(signal):
        print(f, " - ", abs(f))