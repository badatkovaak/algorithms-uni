pub fn task(n: u32) -> (u32, Vec<u32>) {
    let mut cache = HashMap::<u32, (u32, Vec<u32>)>::new();
    task_internal(n, 1, &mut cache);
    cache.get(&1).unwrap().clone()
}

fn task_internal(n: u32, m: u32, cache: &mut HashMap<u32, (u32, Vec<u32>)>) -> () {
    match cache.get(&m) {
        Some(a) => {
            return;
        }
        None => {}
    }

    if m >= n {
        cache.insert(n, (1, vec![n]));
        return;
    }

    if 3 * m <= n {
        task_internal(n, 3 * m, cache);
    }
    if 2 * m <= n {
        task_internal(n, 2 * m, cache);
    }
    if m + 1 <= n {
        task_internal(n, m + 1, cache);
    }

    let a = cache.get(&m);

    if a.is_some() && a.unwrap().0 == m {
        return;
    }

    let temp: &(u32, Vec<u32>) = vec![
        cache.get(&(3 * m)),
        cache.get(&(2 * m)),
        cache.get(&(m + 1)),
    ]
    .iter()
    .filter(|x| x.is_some())
    .map(|x| x.unwrap())
    .min_by_key(|x| x.0)
    .unwrap();

    let mut result = (temp.0 + 1, temp.1.clone());
    result.1.push(m);

    match cache.get(&m) {
        Some(a) => {
            if a.0 > temp.0 + 1 {
                cache.insert(m, result);
            }
        }
        None => {
            cache.insert(m, result);
        }
    }
}

fn main() {
    task(43274);
}
