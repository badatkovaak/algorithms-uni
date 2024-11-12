#[derive(Debug, Clone, Copy)]
pub enum Direction {
    Forward(u32),
    Backward(u32),
}

use Direction as D;

pub fn task4(n: u32) -> (u32, Vec<u32>) {
    let mut stack = Vec::with_capacity(n as usize);
    stack.push(D::Forward(1));
    let mut cache = HashMap::<u32, (u32, Vec<u32>)>::with_capacity(n as usize);

    while stack.len() > 0 {
        let item = stack.pop();
        assert!(!item.is_none());

        match item.unwrap() {
            D::Forward(m) => {
                if cache.get(&m).is_some() {
                    continue;
                }

                if m >= n {
                    cache.insert(n, (1, vec![n]));
                    continue;
                }

                stack.push(D::Backward(m));

                if 3 * m <= n {
                    stack.push(D::Forward(3 * m));
                }
                if 2 * m <= n {
                    stack.push(D::Forward(2 * m));
                }
                if m + 1 <= n {
                    stack.push(D::Forward(m + 1));
                }
            }
            D::Backward(m) => {
                let a = cache.get(&m);

                if a.is_some() && a.unwrap().0 == m {
                    continue;
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
        }
    }
    //dbg!(&cache);
    return cache.get(&1).unwrap().clone();
}
