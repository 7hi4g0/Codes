use std::thread;

#[no_mangle]
pub extern fn process() {
    let handles: Vec<_> = (1..10).map(|_| {
        thread::spawn(|| {
            let mut _x = 0;

            for _ in (0..500_000_001) {
                _x += 1
            }
        })
    }).collect();

    for h in handles {
        h.join().ok().expect("Could not join a thread!");
    }
}
