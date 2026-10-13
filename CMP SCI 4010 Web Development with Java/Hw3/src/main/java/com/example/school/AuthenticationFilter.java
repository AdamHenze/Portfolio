package com.example.school;

import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.http.HttpHeaders;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Component;
import org.springframework.web.filter.OncePerRequestFilter;

@Component
public class AuthenticationFilter extends OncePerRequestFilter {
	private final JwtService jwtService;

	public AuthenticationFilter(JwtService jwtService) {
		this.jwtService = jwtService;
	}

	@Override
	protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain filterChain)
			throws ServletException, java.io.IOException {
		// Get token from the Authorization header
		String jws = request.getHeader(HttpHeaders.AUTHORIZATION);
		if (jws != null) {
			// Validate token and get user info
			String user = jwtService.getAuthUser(request); // if JWT is valid, user will not be null
			// Package user info into Authentication object
			Authentication authentication = new UsernamePasswordAuthenticationToken(user, null,
					java.util.Collections.emptyList());
			// Store user info in SecurityContextHolder to make it available to other components
			SecurityContextHolder.getContext().setAuthentication(authentication);
		}
		filterChain.doFilter(request, response);
	}
}