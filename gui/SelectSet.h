#pragma once

template <class T>
class SelectSet : public std::set<T> {

public:
	_Pairib insert(const value_type& _Val)
	{	
		auto res = this->insert(_Val);
		CUDARender::getCudaRender()->getCache()->change();
		return res;
	}

};