#include "Bitset.h"

Bitset::Bitset(){
	array.resize(DEFAULT_SIZE);
	fill(array.begin(),array.end(),false);
}

Bitset::~Bitset() {
	array.clear();
}

Bitset::Bitset(vector<bool>& new_bitset) {
	array = new_bitset;
}

Bitset::Bitset(const Bitset& b) {
	array = b.array;
}

void Bitset::clear(){
	fill(array.begin(),array.end(),0);	
}

bool Bitset::empty() const {
	for(uint32_t i=0;i<array.size();++i)
		if(array[i]) return false;
	return true;
}

void Bitset::set(uint32_t i, bool bit) {
	array[i] = bit;
}

uint32_t Bitset::count() const{
	uint32_t cnt=0;
	for(uint32_t i=0; i<array.size();++i)
		if(array[i])
			cnt++;
	return cnt;
}

bool Bitset::operator<(const Bitset& b) const{
	unsigned int s1 = count(), s2 = b.count();
	if(s1<s2)
		return true;
	if(s2<s1)
		return false;
	for(uint32_t i=0;i<array.size();++i){
		if(array[i]!=b.array[i]){
			return array[i]<b.array[i];
		}
	}
	return false;	
}

bool Bitset::operator>(const Bitset& b) const {
	unsigned int s1 = count(), s2 = b.count();
	if(s1<s2)
		return false;
	if(s2<s1)
		return true;
	for(uint32_t i=0;i<array.size();++i){
		if(array[i]!=b.array[i]){
			return array[i]>b.array[i];
		}
	}
	return false;
}

void Bitset::resize(uint32_t n){
	array.resize(n);
}

string Bitset::toString(){
	string s="";
	for(uint32_t i=0;i<array.size();++i){
		if(array[i]) s+='1';
		else s+='0';
	}
	return s;
}

bool Bitset::check(uint32_t i) const {
	if(i>=array.size()) return false;
	return array[i];
}

uint32_t Bitset::size(){
	return array.size();
}

bool Bitset::operator==(const Bitset &bs) const
{
	return array == bs.array;
}

bool Bitset::operator!=(const Bitset &bs) const
{
	return array != bs.array;
}