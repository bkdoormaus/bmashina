// BMASHINA
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright 2017 [bk]door.maus

#ifndef BMASHINA_PRIMITIVES_INVERT_HPP
#define BMASHINA_PRIMITIVES_INVERT_HPP

#include "bmashina/decorator.hpp"

namespace bmashina
{
	template <typename M>
	class Invert : public BasicDecorator<M>
	{
	public:
		using typename BasicNode<M>::Tree;
		using typename BasicNode<M>::Executor;

		Invert() = default;
		~Invert() = default;

		Status update(Executor& executor) override;
	};
}

template <typename M>
bmashina::Status bmashina::Invert<M>::update(Executor& executor)
{
	auto begin = this->tree().children_begin(*this);
	auto end = this->tree().children_end(*this);

	if (begin != end)
	{
		auto result = executor.update(*begin);
		if (result == Status::success)
		{
			return Status::failure;
		}
		else if (result == Status::failure)
		{
			return Status::success;
		}
		else
		{
			return result;
		}
	}

	return Status::failure;
}

#endif
