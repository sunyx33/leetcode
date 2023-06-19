class RandomizedSet {
public:
    RandomizedSet() {

    }
    
    bool insert(int val) {
        if(_map.find(val) != _map.end()) return false;
        _vec.push_back(val);
        _map.emplace(val, _vec.size() - 1);
        return true;
    }
    
    bool remove(int val) {
        if(_map.find(val) == _map.end()) return false;
        _map[_vec.back()] = _map[val];
        swap(_vec.back(), _vec[_map[val]]);
        _map.erase(val);
        _vec.pop_back();
        return true;
    }
    
    int getRandom() {
        int pos = (rand() % _vec.size());
        return _vec[pos];
    }
private:
    unordered_map<int, int> _map;
    vector<int> _vec;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */